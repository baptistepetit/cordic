#!/bin/bash
set -euxo pipefail

# Inspired from this guide:
# https://sangsoonam.github.io/2019/02/08/using-git-worktree-to-deploy-github-pages.html


function delete_deployed_worktree() {
    local WEBSITE_DIST_FOLDER="${1}"

    git worktree remove "${WEBSITE_DIST_FOLDER}"
}

function push_gh_pages_branch() {
    local WEBSITE_DIST_FOLDER="${1}"
    local BRANCH="${2}"

    cd "${WEBSITE_DIST_FOLDER}" || exit 1

    git add --all
    git commit -m "Deploy demo updates"
    git push origin "${BRANCH}"
}

function push_and_clean() {
    local WEBSITE_DIST_FOLDER="${1}"
    local BRANCH="${2-"gh-pages"}"

    push_gh_pages_branch \
        "${WEBSITE_DIST_FOLDER}" \
        "${BRANCH}"

    delete_deployed_worktree \
        "${WEBSITE_DIST_FOLDER}"
}


push_and_clean "${@}"
