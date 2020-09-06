# setup dependencies
apt update
apt install -y make g++

# run
begin=$(date +%s)
make
end=$(date +%s)

# send results
LOGFILE="run.log"
echo "Execution time: $(($end-$begin))" >
echo "File size: $(du -sh test.ppm)" >> $LOGFILE