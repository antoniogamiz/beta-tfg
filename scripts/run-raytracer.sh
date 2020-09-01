# setup dependencies
apt update
apt install -y make g++

# run
begin=$(date +%s)
make
end=$(date +%s)

# convert results
pnmtopng test.ppm > result.png

# send results
LOGFILE="run.log"
echo "Execution time: $(($end-$begin))" > $LOGFILE