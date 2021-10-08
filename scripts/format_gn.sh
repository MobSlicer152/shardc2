#!/usr/bin/env bash

gn format `find -type f | grep -i '\.gn$'`

