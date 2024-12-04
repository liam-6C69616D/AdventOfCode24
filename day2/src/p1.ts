import fs from 'fs';

let input : string = fs.readFileSync(__dirname + '/../input.txt', 'utf-8');

function ascending(values : number[]) : boolean {
    let trend = true;
    for (let i=0; i<values.length-1; i++) {
        if (values[i] >= values[i+1] || Math.abs(values[i+1] - values[i]) > 3) trend = false;
    }

    return trend;
}

function descending(values : number[]) : boolean {
    let trend = true;
    for (let i=0; i<values.length-1; i++) {
        if (values[i] <= values[i+1] || Math.abs(values[i+1] - values[i]) > 3) trend = false;
    }

    return trend;
}

let safeCount = 0;

input.split('\n').forEach((row) => {
    let values : number[] = row.split(' ').map((elem) => parseInt(elem));
    if (ascending(values) || descending(values)) safeCount++;
});

console.log(safeCount);