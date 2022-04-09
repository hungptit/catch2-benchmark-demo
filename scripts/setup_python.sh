#!/usr/bin/env bash
root_dir="$PWD"

pushd "$root_dir" || exit

echo Install required Python packages...
env_dir="$root_dir/.local/venv"

echo "Configure the Python virtual environment in " "$env_dir"...

rm -rf "$env_dir"
python3 -mvenv "$env_dir"
"${env_dir}"/bin/pip install --upgrade pip
"${env_dir}"/bin/pip install -U -r scripts/requirements.txt

popd || exit
