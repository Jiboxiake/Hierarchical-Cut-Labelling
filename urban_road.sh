#!/bin/bash

BASE_DIR="/scratch1/zhou822/urban_road_sources"

for dir in "$BASE_DIR"/*/; do
  base=$(basename "$dir")
  csv_path="$dir${base}_Edgelist.csv"

  if [ -f "$csv_path" ]; then
    echo "Running on $csv_path"
    numactl -N 1 -l ./cut "$csv_path"
  else
    echo "❌ CSV not found: $csv_path"
  fi
done