#!/bin/bash
set -euxo pipefail

# Inspired from this guide:
# https://sangsoonam.github.io/2019/02/08/using-git-worktree-to-deploy-github-pages.html


function setup_deployable_worktree() {
    local WEBSITE_DIST_FOLDER="${1}"
    local BRANCH="${2}"

    git push origin --delete "${BRANCH}"
    git branch -D "${BRANCH}"

    git checkout --orphan "${BRANCH}"
    git reset --hard
    git commit --allow-empty -m "Init"
    git checkout main

    rm -rf "${WEBSITE_DIST_FOLDER}"

    git worktree add "${WEBSITE_DIST_FOLDER}" "${BRANCH}"
}

function delete_deployed_worktree() {
    local WEBSITE_DIST_FOLDER="${1}"

    git worktree remove "${WEBSITE_DIST_FOLDER}"
}

function build() {
    local WEBSITE_SOURCES_FOLDER="${1}"

    npm ci --prefix "${WEBSITE_SOURCES_FOLDER}"
    npm run build --prefix "${WEBSITE_SOURCES_FOLDER}"
}

function deploy() {
    local WEBSITE_DIST_FOLDER="${1}"
    local BRANCH="${2}"

    cd "${WEBSITE_DIST_FOLDER}" &&
    git add --all &&
    git commit -m "Deploy demo updates" &&
    git push origin "${BRANCH}"
}

function main() {
    local WEBSITE_SOURCES_FOLDER="${1}"
    local BRANCH="${2-"gh-pages"}"

    local WEBSITE_DIST_FOLDER="${WEBSITE_SOURCES_FOLDER}/dist"

    setup_deployable_worktree \
        "${WEBSITE_DIST_FOLDER}" \
        "${BRANCH}"

    build \
        "${WEBSITE_SOURCES_FOLDER}"

    deploy \
        "${WEBSITE_DIST_FOLDER}" \
        "${BRANCH}"

    delete_deployed_worktree \
        "${WEBSITE_DIST_FOLDER}"
}


main "${@}"
