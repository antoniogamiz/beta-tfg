# generate token and doctl auth init
# genereate ssh fingerprint
key_md5="$(ssh-keygen -l -E md5 -f ~/.ssh/id_rsa.pub | cut -d ' ' -f2)"
key_md5="${key_md5##MD5:}"

doctl compute droplet create RayTracer --image ubuntu-20-04-x64 --size c-2 --region nyc1 --ssh-keys $key_md5

# to disable known_hosts warning (not recommended): https://superuser.com/a/853144/1161534
# Warning: Using the doctl Snap? Grant access to the ssh-keys interface with this command: sudo snap connect doctl:ssh-keys

doctl compute ssh RayTracer --ssh-command 'git clone -b raytracing-bookseries https://github.com/antoniogamiz/tfg.git repo && export DO_TOKEN=$DO_TOKEN && cd repo && noup bash scripts/run-raytracer.sh &'
