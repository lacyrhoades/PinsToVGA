<?php

$rows = 64;
$cols = 16;

echo "{";
for ($j = 0; $j < $rows; $j++) {
  echo "{";
  for ($k = 0; $k < $cols; $k++) {
    echo "B" . rand(0, 1) . rand(0, 1) . rand(0, 1) . rand(0, 1) . rand(0, 1) . rand(0, 1) . rand(0, 1) . rand(0, 1);
    if ($k < $cols - 1) {
      echo ", ";
    }
  }
  echo "}";
  echo "\n";

  if ($j < $rows - 1) {
    echo ", ";
  }
}
echo "}";

echo "\n";
