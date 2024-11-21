
const createSelector = f => {
    const ret = {
        result: null,
        steps: [],
    }
    const tracker = (keys, object) => {
        const A = {};
        if (object === null || object === undefined)
            return;
        for (const key of Object.getOwnPropertyNames(object)) {
            Object.defineProperty(A, key, {
                get() {
                    const qqq = [...keys, key];
                    const inner = object[key];
                    if (!inner || typeof inner != 'object') {
                        console.log('END', qqq, inner);
                        ret.steps.push(qqq);
                        return inner;
                    }
                    console.log('REC', qqq, inner, typeof inner, !inner || typeof inner != 'object');
                    return tracker(qqq, inner);
                }
            })
        }
        return A;
    }
    const wrap = (keys, object) => tracker(keys, object);
    return (state, params) => {
        ret.result = f(wrap(['arg0'], state), wrap(['arg1'], params));
        const rettt = {
            result: ret.result,
            steps: [...ret.steps],
        };
        ret.steps = []
        return rettt;
    };
};
module.exports = createSelector;

const selector1 = createSelector((state) => {
    if (state.isEnabled) {
        return state.inner.value;
    }

    return null;
});

const selector2 = createSelector((state) => {
    if (Array.isArray(state.array) && state.array.length > 0) {
        return state.array[0];
    }

    return null;
});

const result1 = selector1({ isEnabled: true, inner: { value: 42 } })
const result2 = selector1({ isEnabled: false, inner: { value: 21 } })
const result3 = selector2({ array: [1, 2, 3] });

const obj1 = {
    result: 42,
    steps: [
        ["arg0", "isEnabled"],
        ["arg0", "inner", "value"],
    ],
}

const obj2 = {
    result: null,
    steps: [["arg0", "isEnabled"]],
}

const obj3 = {
    result: 1,
    steps: [
        ["arg0", "array", "length"], 
        ["arg0", "array", "0"]
    ],
}

//console.log(result1, obj1);
console.log(result3, obj3);
console.log(JSON.stringify(result1) === JSON.stringify(obj1)) // true
console.log(JSON.stringify(result2) === JSON.stringify(obj2)) // true
console.log(JSON.stringify(result3) === JSON.stringify(obj3)) // true
