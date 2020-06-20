echo $1
echo ---------------------------------- 
echo 'Running Debian_cpp container...' 
echo ---------------------------------- 
echo Building source code
echo ... Building file $1 ... 
[ -e /Projects/$1.out ] && 
rm /Projects/$1.out 

export PATH=/usr/bin/clang++-10/bin:$PATH 
export LD_LIBRARY_PATH=/usr/lib/clang/10.0.0/lib:$LD_LIBRARY_PATH
export LD_INCLUDE_PATH=/usr/local/include/boost:$LD_INCLUDE_PATH 
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH 

if /usr/bin/clang++-10 -I/usr/lib/llvm-9/include/c++/v1 -I /usr/local/include/boost -L/usr/lib/llvm-9/lib -L/usr/local/lib -std=c++17 -stdlib=libc++ /Projects/$1 -Wall -pthread \
    -fcoroutines-ts -Xclang \
    -D_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR -o /Projects/$1.out
then echo Compilation succeeded && 
     echo ---------------------------------- && 
     echo Output: && ./Projects/$1.out 
else echo Compilation failed! 
fi  

[ -e /Projects/$1.out ] && 
rm /Projects/$1.out