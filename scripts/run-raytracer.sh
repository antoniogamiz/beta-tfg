# setup dependencies
snap install doctl
apt update
apt install -y make g++ mutt sendmail netpbm

# run
begin=$(date +%s)
make
end=$(date +%s)

# convert results
pnmtopng test.ppm > result.png

# send results
BODY="Execution time: $(($end-$begin)), File size: $(du -sh test.ppm)"
echo $BODY | mutt -a "./result.png" -s "Run $(date)" -- antoniogamiz10@gmail.com