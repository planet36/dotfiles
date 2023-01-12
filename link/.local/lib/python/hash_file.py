# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=invalid-name
# pylint: disable=line-too-long
# pylint: disable=missing-function-docstring
# pylint: disable=missing-module-docstring

__author__ = 'Steven Ward'
__version__ = '2022-09-08'
__license__ = 'OSL-3.0'

import hashlib
import sys

def hash_file(file_name, hash_object=None, block_size=65536):
    """Open file_name, read block_size bytes at a time, and hash the bytes using the hash_object.

hash_object is a hash object created by hashlib.new <https://docs.python.org/dev/library/hashlib.html#hashlib.new> or the corresponding named constructor.

If hash_object is not given, the md5 algorithm is used.

block_size must not be greater than sys.maxsize.  If block_size is too large, a MemoryError might be raised.

It's recommended that block_size be a power-of-2 multiple of 4096.  Suggested block_size values follow.
 32768 (== 4096 *  8)
 65536 (== 4096 * 16)
131072 (== 4096 * 32)
262144 (== 4096 * 64)

This function was inspired by <https://web.archive.org/web/20100609151224/https://www.pytips.com/2010/5/29/a-quick-md5sum-equivalent-in-python>."""

    if hash_object is None:
        hash_object = hashlib.md5()

    with open(file_name, mode='rb') as f:

        while True:

            file_data = f.read(block_size)

            if not file_data:
                break

            hash_object.update(file_data)

    return hash_object

# pylint: disable=too-many-branches
# pylint: disable=too-many-locals
# pylint: disable=too-many-return-statements
# pylint: disable=too-many-statements
def main(argv = None):

    # pylint: disable=import-outside-toplevel
    import base64
    import getopt
    import os.path
    import shlex
    import signal

    if argv is None:
        argv = sys.argv

    program_name = os.path.basename(argv[0])

    # valid values
    valid_hash_algorithms = hashlib.algorithms_guaranteed
    valid_formats = {'b16' : base64.b16encode, 'b32' : base64.b32encode, 'b64-std' : base64.standard_b64encode, 'b64-url' : base64.urlsafe_b64encode}

    # default values
    default_hash_algorithm = 'md5'
    default_block_size = 65536
    default_format = 'b16'

    # mutable values
    hash_algorithm = default_hash_algorithm
    block_size = default_block_size
    fmt = default_format

    # pylint: disable=unused-argument
    def signal_handler(signal_num, execution_frame):
        print()
        sys.exit(0)

    signal.signal(signal.SIGINT, signal_handler) # Interactive attention signal. (Ctrl-C)
    signal.signal(signal.SIGTERM, signal_handler) # Termination request. (kill default signal)

    def print_version():
        """Print the version information"""
        print(program_name, __version__)
        print("License:", __license__)
        print("Written by", __author__)

    # pylint: disable=unused-variable
    def print_warning(s):
        """Print the warning message"""
        print(f"Warning: {s}", file=sys.stderr)

    def print_error(s):
        """Print the error message"""
        print(f"Error: {s}", file=sys.stderr)
        print(f"Try '{program_name} --help' for more information.", file=sys.stderr)

    def print_help():
        """Print the help message"""

        print(f"""Usage: {program_name} [OPTIONS] [FILE...]
Print the hash digest of FILE(s).

If FILE is absent, or if FILE is '-', read standard input.

OPTIONS

-V, --version
    Print the version information, then exit.

-h, --help
    Print this message, then exit.

-a, --hash-algorithm=ALGORITHM
    Use hash algorithm ALGORITHM to hash the file.
    (default: {default_hash_algorithm})
    (valid: {','.join(sorted(valid_hash_algorithms))})
    <https://docs.python.org/3/library/hashlib.html>

-b, --block-size=N
    Read N bytes at a time from FILE.
    (default: {default_block_size})

-f, --format=FORMAT
    Print the hash in FORMAT encoding.
    <https://docs.python.org/3/library/base64.html>
    (default: {default_format})
    (valid: {','.join(sorted(valid_formats.keys()))})
""")

    short_options = 'Vha:b:f:'
    long_options = ['version', 'help', 'hash-algorithm=', 'block-size=', 'format=']

    try:
        (options, remaining_args) = getopt.getopt(argv[1:], short_options, long_options)
    except getopt.GetoptError as err:
        print_error(err)
        return 1

    for (option, value) in options:
        # pylint: disable=no-else-return
        if option in ['-V', '--version']:
            print_version()
            return 0
        elif option in ['-h', '--help']:
            print_help()
            return 0
        elif option in ['-a', '--hash-algorithm']:
            hash_algorithm = value
            assert hash_algorithm in valid_hash_algorithms
        elif option in ['-b', '--block-size']:
            block_size = int(value)
        elif option in ['-f', '--format']:
            fmt = value
            assert fmt in valid_formats
        else:
            print_error(f"Unhandled option: {option}")
            return 1

    # No file was given.
    if not remaining_args: # empty
        remaining_args.append('-')

    for file_name in remaining_args:

        file_name_quoted = shlex.quote(file_name)

        hash_object = hashlib.new(hash_algorithm)

        if file_name == '-': # Hash standard input.

            while True:

                # Use the binary buffer to read bytes from stdin.
                file_data = sys.stdin.buffer.read(block_size)

                if not file_data:
                    break

                hash_object.update(file_data)

        else: # Hash the file.

            hash_object = hash_file(file_name, hash_object, block_size)

        hash_digest = hash_object.digest()
        print(f'{valid_formats[fmt](hash_digest).decode()}  {file_name_quoted}')

if __name__ == '__main__':
    sys.exit(main())
