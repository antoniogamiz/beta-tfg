DROPLET_NAME=$( doctl compute droplet list --format "Name" | tail -n1  | tr -d '\n')

while :
do
    output=$(doctl compute ssh $DROPLET_NAME --ssh-command "cd repo && bash show_progress.sh")
    echo $output
    sleep 1
done