#!/bin/bash
set -euxo pipefail

# Inspired from this guide:
# https://sangsoonam.github.io/2019/02/08/using-git-worktree-to-deploy-github-pages.html


function setup_deployable_worktree() {
    local WEBSITE_DIST_FOLDER="${1}"
    local BRANCH="${2-"gh-pages"}"

    git push origin --delete "${BRANCH}"

    git checkout --orphan "${BRANCH}"
    git reset --hard
    git commit --allow-empty -m "Init"
    git checkout main

    rm -rf "${WEBSITE_DIST_FOLDER}"

    git worktree add "${WEBSITE_DIST_FOLDER}" "${BRANCH}"
}


setup_deployable_worktree "${@}"
