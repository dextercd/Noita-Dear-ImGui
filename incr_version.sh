#!/bin/bash

set -e

# Git check

(git diff --quiet && git diff --staged --quiet) || (
    echo "Git not clean.. not continuing" >&2
    exit 1)


# Calculate next version

version_line=$(sed -n '/^\s*\<VERSION\> [0-9]/p' CMakeLists.txt)

if [[ ! $version_line =~ ([0-9]+)\.([0-9]+)\.([0-9]+)\.([0-9]+)$ ]]; then
    echo "Couldn't find version string" >&2
    exit 1
fi

major=${BASH_REMATCH[1]}
minor=${BASH_REMATCH[2]}
patch=${BASH_REMATCH[3]}
tweak=${BASH_REMATCH[4]}

case "$1" in
    major) ((++major)); minor=0; patch=0; tweak=0 ;;
    minor) ((++minor)); patch=0; tweak=0 ;;
    patch) ((++patch)); tweak=0 ;;
    tweak) ((++tweak)) ;;
    *) echo "Unknown version component '$1'"; exit 1 ;;
esac

without_tweak="$major.$minor.$patch"
new_version="$without_tweak.$tweak"
echo "Next version: $new_version"


# Todos

todo() {
    while true; do
        echo "TODO: $1" [y]

        read -r input
        case "$input" in
            y) return
        esac
    done
}

todo "Build succeeds in Windows"


# Apply changes in repo

sed -i "s/^\(\s*\<VERSION\> \)[0-9.]*$/\1$new_version/" CMakeLists.txt

git add CMakeLists.txt
git commit -m "Release $without_tweak"
git tag "release-$without_tweak"

echo
echo git push origin HEAD --tags
