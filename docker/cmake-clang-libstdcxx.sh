echo ----------------------------------
echo 'Running Debian_cpp container...'
echo ----------------------------------

echo Building source code
echo ... Going to Project folder

echo ... Adding /usr/bin/clang++-6.0/bin to PATH variable && 
export PATH=/usr/bin/clang++-6.0/bin:$PATH 
echo ... Adding /usr/lib/clang/6.0/lib to LD_LIBRARY_PATH variable && 
export LD_LIBRARY_PATH=/usr/lib/clang/6.0/lib:$LD_LIBRARY_PATH
export POLLY_ROOT=/polly-0.10.3

echo Setting up cmake modules
cd Projects

/polly-0.10.3/bin/polly.py > out.log 2> err.log
/polly-0.10.3/bin/polly.py &> out.log      # New bash syntax
/polly-0.10.3/bin/polly.py > out.log 2>&1  # Older sh syntax
/polly-0.10.3/bin/polly.py > out.log 2> /dev/null

# and run cmake only
echo ... Running cmake .
cmake -H. -B_builds/clang-libstdcxx -DCMAKE_TOOLCHAIN_FILE=${POLLY_ROOT}/clang-libstdcxx.cmake -DCMAKE_VERBOSE_MAKEFILE=ON 

echo ... Output
/Projects/_builds/default/run_linux 
rm -rd /Projects/_builds && 
rm -rd /Projects/_logs &&
rm err.log && 
rm out.log