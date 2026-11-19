"""Check the actual executable's arguments, output streams and moves."""
import itertools
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'Sorting' / 'tests'))
from test_sorting import replay


def run(arguments):
    return subprocess.run([str(ROOT / 'push_swap'), *arguments],
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


def main():
    count = 0
    print('\n  PUSH_SWAP / COMMAND-LINE TESTS\n', flush=True)
    for size in range(2, 6):
        for values in itertools.permutations(range(1, size + 1)):
            values = list(values)
            valid(list(map(str, values)), values)
            count += 1
    print(f'  [PASS] {count} permutations through the real executable')
    cases = [([], []), (['0'], [0]), (['3 1 2'], [3, 1, 2]),
             ([' 3\t1 ', '+2'], [3, 1, 2]),
             (['2147483647 -2147483648 0'], [2147483647, -2147483648, 0]),
             (['10 9 8 7 6 5 4 3 2 1'], list(range(10, 0, -1)))]
    for arguments, values in cases:
        valid(arguments, values)
    print('  [PASS] Empty, single, quoted, mixed and boundary input')
    bad = [[''], ['   '], ['+'], ['-'], ['1x'], ['2147483648'],
           ['-2147483649'], ['1', '1'], ['0', '-0'], ['+1', '01'],
           ['3 2', '2'], ['3 2', 'bad'], ['- 12'], ['1', ''],
           ['1', '\t'], ['999999999999999999999999999999']]
    for arguments in bad:
        result = run(arguments)
        if result.returncode != 1 or result.stdout or result.stderr != 'Error\n':
            raise RuntimeError(f'{arguments!r}: expected exit 1, empty stdout, '
                               f'Error on stderr; got {result.returncode}, '
                               f'{result.stdout!r}, {result.stderr!r}')
    print('  [PASS] Invalid input and duplicates: exact error output and exit status')
    print(f'\n  All {count + len(cases) + len(bad)} CLI cases passed.\n')
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (RuntimeError, subprocess.TimeoutExpired) as error:
        print(f'[FAIL] {error}', file=sys.stderr)
        sys.exit(1)
