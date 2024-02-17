#!/bin/bash

echo "make"
make

(sleep 5; pkill emu) &

echo "./emu"
./emu > test_log/result.log

diff test_log/result.log test_log/cputest_result.log > test_log/cputest_diff.log
vim test_log/cputest_diff.log
