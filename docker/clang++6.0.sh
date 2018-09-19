echo $1
echo ---------------------------------- 
echo 'Running Debian_cpp container...' 
echo ---------------------------------- 
echo Building source code
echo ... Building file $1 ... 
[ -e /Projects/$1.out ] && 
echo ...Removing existing executable file $1.out && 
echo rm /Projects/$1.out && 
rm /Projects/$1.out 

echo ... Adding /usr/bin/clang++-6.0/bin to PATH variable && 
export PATH=/usr/bin/clang++-6.0/bin:$PATH 
echo ... Adding /usr/lib/clang/6.0.1/lib to LD_LIBRARY_PATH variable && 
export LD_LIBRARY_PATH=/usr/lib/clang/6.0.1/lib:$LD_LIBRARY_PATH

echo ... Adding /usr/local/include/boost to LD_INCLUDE_PATH variable && 
export LD_INCLUDE_PATH=/usr/local/include/boost:$LD_INCLUDE_PATH 
echo ... Adding /usr/local/lib to LD_LIBRARY_PATH variable && 
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH 

echo clang++ -std=c++17 -stdlib=libc++ -Wall --pedantic /Projects/$1 -o /Projects/$1.out
if /usr/bin/clang++-6.0 -I /usr/local/include/boost -L/usr/local/lib -std=c++1z -stdlib=libc++ /Projects/$1 -Wall \
    -D_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR -o /Projects/$1.out -lc++experimental
then echo Compilation succeeded && 
     echo ---------------------------------- && 
     echo Output: && ./Projects/$1.out 
else echo Compilation failed! 
fi  

[ -e /Projects/$1.out ] && 
echo && 
echo ---------------------------------- && 
echo Removing executable file $1.out && 
rm /Projects/$1.out