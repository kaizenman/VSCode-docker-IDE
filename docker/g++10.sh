echo ---------------------------------- 
echo 'Running Debian_cpp container...' 
echo ----------------------------------
echo Building source code 
echo ... Building file $1 ... 

[ -e /Projects/$1.out ] && 
echo ...Removing existing executable file $1.out && 
echo rm /Projects/$1.out && 
rm /Projects/$1.out

g++ /Projects/$1 -o /Projects/$1.out -lstdc++fs

echo Output: && 
./Projects/$1.out 

rm /Projects/$1.out