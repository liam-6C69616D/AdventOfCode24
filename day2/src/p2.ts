import fs from 'fs';

let input : string = fs.readFileSync(__dirname + '/../input.txt', 'utf-8');

function ascending(values : number[]) : boolean {
    let trend : boolean = true;
    for (let i=0; i<values.length-1; i++) {
        if (values[i] >= values[i+1] || Math.abs(values[i+1] - values[i]) > 3) trend = false;
    }

    return trend;
}

function descending(values : number[]) : boolean {
    let trend : boolean = true;
    for (let i=0; i<values.length-1; i++) {
        if (values[i] <= values[i+1] || Math.abs(values[i+1] - values[i]) > 3) trend = false;
    }

    return trend;
}

let safeCount : number = 0;

input.split('\n').forEach((row) => {
    let values : number[] = row.split(' ').map((elem) => parseInt(elem));
    let dampenedValues : number[][] = [];
    for (let i=0; i<values.length; i++) {
        let dampArr : number[] = [...values.slice(0, i), ...values.slice(i+1)];
        dampenedValues.push(dampArr);
    }

    let safe : boolean = false;
    dampenedValues.forEach((arr) => {
        if (ascending(arr) || descending(arr)) safe = true;
    });
    
    if (ascending(values) || descending(values)) safe = true;

    if (safe) safeCount++;
});

console.log(safeCount);