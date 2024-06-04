#!/usr/bin/bash

set -ex

eval $(git for-each-ref --shell \
  --format='git checkout %(objectname) && poetry run mike deploy %(refname:lstrip=2);' \
  --exclude=refs/remotes/origin/gh-pages  \
   refs/remotes/origin)
poetry run mike set-default main
git checkout gh-pages