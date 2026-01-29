#!/bin/bash
NAMESPACE="${1:-codebase_b599_app}"
docker build -t "$NAMESPACE" .