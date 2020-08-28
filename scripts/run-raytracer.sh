# setup dependencies
snap install doctl
apt update
apt install -y make g++ mutt sendmail
# doctl auth init --access-token $DO_TOKEN

# run
begin=$(date +%s)
make
end=$(date +%s)

# convert results
pnmtopng test.ppm > result.png

# send results
echo "Execution time: $(($end-$begin))" | mutt -a "./result.png" -s "Run $(date)" -- antoniogamiz10@gmail.com

# doctl compute droplet delete RayTracer