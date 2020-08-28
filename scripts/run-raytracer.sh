# setup dependencies
snap install doctl
apt intall update
apt install -y make g++ mutt sendmail
doctl auth init --access-token $DO_TOKEN

# run
make

# convert results
pnmtopng test.ppm > result.png

# send results
echo "" | mutt -a "./result.png" -s "Run $(date)" -- antoniogamiz10@gmail.com

# doctl compute droplet delete RayTracer