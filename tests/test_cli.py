"""Check the actual executable's arguments, output streams and moves."""
import itertools
import argparse
from pathlib import Path
import random
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'Sorting' / 'tests'))
from test_sorting import replay

BINARY = ROOT / 'push_swap'
STRATEGIES = [(), ('--simple',), ('--medium',), ('--complex',), ('--adaptive',)]


def run(arguments):
    return subprocess.run([str(BINARY), *arguments],
                          capture_output=True, text=True, timeout=5)


def valid(arguments, values):
    result = run(arguments)
    if result.returncode or result.stderr:
        raise RuntimeError(f'{arguments!r}: unexpected failure {result.stderr!r}')
    if result.stdout and not result.stdout.endswith('\n'):
        raise RuntimeError('Missing newline in instruction output')
    moves = result.stdout.splitlines()
    replay(values, moves)
    if values == sorted(values) and moves:
        raise RuntimeError('Sorted input should produce no output')
    return len(moves)


def inversion_case(size, mistakes):
    """Construct an input with an exact inversion count for dispatch tests."""
    remaining = list(range(size))
    values = []
    while remaining:
        index = min(mistakes, len(remaining) - 1)
        values.append(remaining.pop(index))
        mistakes -= index
    return values


def main():
    count = 0
    print('\n  PUSH_SWAP / COMMAND-LINE TESTS\n', flush=True)
    for strategy in STRATEGIES:
        for size in range(2, 6):
            for values in itertools.permutations(range(1, size + 1)):
                values = list(values)
                valid([*strategy, *map(str, values)], values)
                count += 1
        print(f'  [PASS] {strategy[0] if strategy else "default":12} '
              'all 152 permutations of 2-5 values', flush=True)
    cases = [([], []), (['0'], [0]), (['3 1 2'], [3, 1, 2]),
             ([' 3\t1 ', '+2'], [3, 1, 2]),
             (['2147483647 -2147483648 0'], [2147483647, -2147483648, 0]),
             (['10 9 8 7 6 5 4 3 2 1'], list(range(10, 0, -1)))]
    for strategy in STRATEGIES:
        for arguments, values in cases:
            valid([*strategy, *arguments], values)
            count += 1
    print('  [PASS] Empty, single, quoted, mixed and boundary input')
    bad = [[''], ['   '], ['+'], ['-'], ['1x'], ['2147483648'],
           ['-2147483649'], ['1', '1'], ['0', '-0'], ['+1', '01'],
           ['3 2', '2'], ['3 2', 'bad'], ['- 12'], ['1', ''],
           ['1', '\t'], ['999999999999999999999999999999']]
    bad += [['--unknown', '1'], ['--complex', '--medium', '2', '1'],
            ['1', '--simple'], ['--'], ['1\x7f']]
    for strategy in STRATEGIES:
        for arguments in bad:
            result = run([*strategy, *arguments])
            if result.returncode != 1 or result.stdout or result.stderr != 'Error\n':
                raise RuntimeError(f'{strategy!r} {arguments!r}: expected exit 1, '
                                   'empty stdout, Error on stderr; got '
                                   f'{result.returncode}, {result.stdout!r}, '
                                   f'{result.stderr!r}')
            count += 1
    print('  [PASS] Invalid input and duplicates: exact error output and exit status')

    # Check both sides of the adaptive thresholds: 20% and 50% of 45 pairs.
    for mistakes in (0, 1, 8, 9, 22, 23, 45):
        values = inversion_case(10, mistakes)
        actual = sum(x > y for i, x in enumerate(values) for y in values[i + 1:])
        if actual != mistakes:
            raise RuntimeError('Invalid adaptive test input')
        selected = ('--simple' if mistakes * 5 < 45 else
                    '--medium' if mistakes * 2 < 45 else '--complex')
        args = list(map(str, values))
        expected = run([selected, *args])
        for strategy in ((), ('--adaptive',)):
            valid([*strategy, *args], values)
            result = run([*strategy, *args])
            if result.stdout != expected.stdout:
                raise RuntimeError(f'Wrong adaptive strategy at {mistakes}/45 inversions')
            count += 1
    print('  [PASS] Adaptive dispatch at and around both disorder thresholds', flush=True)

    print('\n  Large inputs: replay verified; min / average / max moves')
    for size in (100, 500):
        rng = random.Random(42000 + size)
        ordered = list(range(size))
        nearly = ordered.copy()
        nearly[0], nearly[1] = nearly[1], nearly[0]
        zigzag = ordered[::2] + ordered[1::2][::-1]
        samples = [ordered, ordered[::-1], nearly, zigzag]
        samples += [rng.sample(range(-2147483648, 2147483648), size)
                    for _ in range(5)]
        for strategy in STRATEGIES:
            moves = [valid([*strategy, *map(str, values)], values) for values in samples]
            count += len(samples)
            print(f'  [PASS] n={size:3} {strategy[0] if strategy else "default":12} '
                  f'{min(moves):5} / {sum(moves)/len(moves):8.1f} / {max(moves):5}',
                  flush=True)
    print(f'\n  All {count} CLI cases passed.\n')
    return 0


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--binary', default='push_swap',
                        help='Executable path relative to the project root')
    BINARY = (ROOT / parser.parse_args().binary).resolve()
    try:
        sys.exit(main())
    except (RuntimeError, subprocess.TimeoutExpired) as error:
        print(f'[FAIL] {error}', file=sys.stderr)
        sys.exit(1)
