#! /bin/bash
echo "Hello World"
read -r n
index=0
sum=0
while ((index <= n))
do
    ((sum += index))
    ((index++))
done
echo "$sum"