# Previous steps:
# 1. Generate token and run doctl auth init --access-token $TOKEN
# 2. Generate a ssh fingerprint
# 3. Disable known_hosts warning (https://superuser.com/a/853144/1161534)
# 4. Create spam filter for root@raytracer.com in gmail

# ============================== SETTINGS ==============================

DROPLET_NAME="RayTracer"
DROPLET_SIZE="c-32"
BRANCH_NAME="raytracing-bookseries"

# ============================== SETUP DROPLET ==============================


NUMBER_OF_DROPLETS=$( doctl compute droplet list --format "PublicIPv4" | wc -l )
if [ $NUMBER_OF_DROPLETS -eq 2 ]
then
    echo "Droplet already running. Skipping..."
else
    key_md5="$(ssh-keygen -l -E md5 -f ~/.ssh/id_rsa.pub | cut -d ' ' -f2)"
    key_md5="${key_md5##MD5:}"

    doctl compute droplet create $DROPLET_NAME --image ubuntu-20-04-x64 --size c-32 --region nyc1 --ssh-keys $key_md5
    sleep 3
    doctl compute ssh $DROPLET_NAME --ssh-command 'git clone -b $BRANCH_NAME https://github.com/antoniogamiz/tfg.git repo && cd repo && nohup bash scripts/run-raytracer.sh &'
fi

# ============================== CHECK PROGRESS ==============================

DROPLET_IP=$( doctl compute droplet list --format "PublicIPv4" | tail -n1  | tr -d '\n')

output=$(doctl compute ssh $DROPLET_NAME --ssh-command "cd repo && bash scripts/progress.sh")
while [ "$output" != "Ray tracer is not running!" ]:
do
    echo $output
    sleep 2
    output=$(doctl compute ssh $DROPLET_NAME --ssh-command "cd repo && bash scripts/progress.sh")
done

# ============================== STORE RESULTS ==============================

rsync -a root@$DROPLET_IP:/root/repo/result.png doresults/result.png
rsync -a root@$DROPLET_IP:/root/repo/test.ppm doresults/test.ppm

doctl compute droplet delete $DROPLET_NAME