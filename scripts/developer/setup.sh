#!/bin/bash


# Get github username
read -p "Github username: " github_username
if test -z "$var" then
	echo "Github username can't be empty"
	exit
fi

echo "Checking SSH Github access"
ssh -o ConnectTimeout=10 -T git@github.com 2>/dev/null

if [ $? -eq 1 ]
then
  echo "SSH Github sucess"
  git config remote.origin.pushurl "git@github.com:${github_username}/ADIOS2-Examples.git"
else
  echo "SSH Github failed.  Using HTTPS."
  git config remote.origin.pushurl https://${github_username}@github.com/${github_username}/ADIOS2-Examples.git
fi

git checkout master
git remote rm upstream
git remote add upstream https://github.com/ornladios/ADIOS2.git

echo "Local master branch to use upstream"
git config branch.master.remote upstream
git config branch.master.mergeOptions "--ff-only"
git config merge.log 20
git fetch --all -p

exit 0