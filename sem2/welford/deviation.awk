#!/usr/bin/awk -f

{

    sum += $1
    sum2 += $1*$1

}

END {

    mean = sum / NR
    deviation = sqrt(sum2 / NR - mean^2)

    printf "Size = %d.\n", NR
    printf "Mean = %.6f.\n", mean
    printf "Deviation = %.6f.\n", deviation

}

