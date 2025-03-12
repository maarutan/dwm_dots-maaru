#!/usr/bin/env python3

# push dotfiles \ logic file
# https://github.com/maaru/dotfiles.git
# Copyright (c) 2025 maarutan \ Marat Arzymatov. All Rights Reserved.

# DONE: ------=== Imports ===------
import os
import subprocess
import sys
import pathlib

# DONE: ------=== Variables ===------

CACHE_DIR = pathlib.Path(__file__).parent / ".cache"
CACHE_DIR.mkdir(exist_ok=True)

BRANCH_FILE_NAME = "current_git_branch"
CLOUD_REPO_FILE_NAME = "current_cloud_repo"

CACHE_GIT_BRANCH = CACHE_DIR / BRANCH_FILE_NAME
CACHE_CLOUD_REPO = CACHE_DIR / CLOUD_REPO_FILE_NAME

RESULT_DIR = pathlib.Path(__file__).parent / "dist"

# INFO: for git
GIT_CLONE = "git clone --depth 1"
GIT_PULL = "git pull"
GIT_PUSH = "git push"

# INFO: for reset local repo to remote
GIT_CLEAN = "git clean -fdx"
GIT_RESET = "git reset --hard origin/$(git rev-parse --abbrev-ref HEAD)"
GIT_FETCH = "git fetch --all"


# DONE: ------=== Functions ===------


def shell(command) -> str | None:
    blacklist = [
        "poweroff",
        "reboot",
        "rm",
        "shutdown",
    ]
    if command.split()[0] in blacklist:
        return print(f"skipping: {command}")
    else:
        return subprocess.run(
            command, shell=True, text=True, capture_output=True
        ).stdout.strip()


def BRANCH(value):
    path = pathlib.Path(__file__).parent / ".cache" / BRANCH_FILE_NAME
    with path.open("w") as f:
        f.write(value)


def CLOUDE_REPO(value):
    path = pathlib.Path(__file__).parent / ".cache" / CLOUD_REPO_FILE_NAME
    with path.open("w") as f:
        f.write(value)


def read_branch_cache_file():
    path = pathlib.Path(__file__).parent / ".cache" / BRANCH_FILE_NAME
    with path.open("r") as f:
        return f.read()


def read_cloud_repo_cache_file():
    path = pathlib.Path(__file__).parent / ".cache" / CLOUD_REPO_FILE_NAME
    with path.open("r") as f:
        return f.read()
