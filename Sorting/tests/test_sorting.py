"""Run every small permutation and independently replay printed instructions."""
import itertools
import os
from pathlib import Path
import subprocess
import sys

COLOR = sys.stdout.isatty() and 'NO_COLOR' not in os.environ
GREEN = '\033[32m' if COLOR else ''
CYAN = '\033[1;36m' if COLOR else ''
RESET = '\033[0m' if COLOR else ''
BINARY = Path(__file__).resolve().with_name('sorting_tests')


def replay(values, instructions):
    a, b = list(values), []
    for instruction in instructions:
        if instruction in ('sa', 'sb', 'ss'):
            for stack in ([a] if instruction == 'sa' else
                          [b] if instruction == 'sb' else [a, b]):
                if len(stack) >= 2:
                    stack[0], stack[1] = stack[1], stack[0]
        elif instruction in ('pa', 'pb'):
            source, destination = (b, a) if instruction == 'pa' else (a, b)
            if source:
                destination.insert(0, source.pop(0))
        elif instruction in ('ra', 'rb', 'rr', 'rra', 'rrb', 'rrr'):
            stacks = ([a] if instruction in ('ra', 'rra') else
                      [b] if instruction in ('rb', 'rrb') else [a, b])
            for stack in stacks:
                if len(stack) >= 2:
                    if instruction in ('rra', 'rrb', 'rrr'):
                        stack.insert(0, stack.pop())
                    else:
                        stack.append(stack.pop(0))
        else:
            raise RuntimeError(f'Unknown instruction: {instruction!r}')
    if a != sorted(values) or b:
        raise RuntimeError(f'Instruction replay failed: A={a}, B={b}')


def run_case(values):
    try:
        result = subprocess.run([str(BINARY), *map(str, values)],
                                capture_output=True, text=True, timeout=5)
    except subprocess.TimeoutExpired as error:
        raise RuntimeError('Timed out (possible infinite loop)') from error
    if result.returncode:
        raise RuntimeError(f'Driver exited {result.returncode}\n{result.stderr}')
    if result.stderr:
        raise RuntimeError(f'Unexpected diagnostics:\n{result.stderr}')
    if result.stdout and not result.stdout.endswith('\n'):
        raise RuntimeError('Instruction output is missing its final newline')
    instructions = result.stdout.splitlines()
    replay(values, instructions)
    if list(values) == sorted(values) and instructions:
        raise RuntimeError('Already sorted input emitted instructions')
    return len(instructions)


def main():
    print('\n  +------------------------------------------------------+')
    print('  |             PUSH_SWAP / SORTING TESTS                 |')
    print('  |                       ppoco                          |')
    print('  +------------------------------------------------------+')
    print('  Node identity, links, sizes, cleanup and instruction replay.')
    suites = [
        ('Three values', (1, 2, 3)),
        ('Four values', (1, 2, 3, 4)),
        ('Five values', (1, 2, 3, 4, 5)),
        ('Three signed values', (-2147483648, 0, 2147483647)),
        ('Four signed values', (-2147483648, -7, 0, 2147483647)),
        ('Five signed values', (-2147483648, -7, 0, 19, 2147483647)),
    ]
    total = 0
    for title, values in suites:
        print(f'\n  {CYAN}{title}{RESET}', flush=True)
        print('  ------------------------------------------------------')
        moves = []
        for permutation in itertools.permutations(values):
            try:
                moves.append(run_case(permutation))
            except RuntimeError as error:
                print(f'  [FAIL] Input: {permutation}\n{error}', file=sys.stderr)
                return 1
        total += len(moves)
        print(f'  {GREEN}[PASS]{RESET} {len(moves):3} permutations | '
              f'moves: min {min(moves)}, max {max(moves)}, '
              f'average {sum(moves) / len(moves):.2f}')
    print(f'\n  {GREEN}All {total} cases passed.{RESET}\n')
    return 0


if __name__ == '__main__':
    sys.exit(main())
