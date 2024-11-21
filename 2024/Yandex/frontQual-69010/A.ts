/** Типы */

type Signal = 'GREEN' | 'LEFT' | 'RIGHT' | 'RED';
type Direction = 'FORWARD' | 'LEFT' | 'RIGHT';

type TrafficLightController = {
    subscribe: (callback: (signal: Signal) => void) => void;
}

interface ITraffic {
    signal: Signal
    go: (direction: Direction) => Promise<void>;
}

class Traffic {
    applyDirection(direction) {
        for (const f of this.directions[direction])
            f();
        this.directions[direction] = []
    }

    checkDirection(signal, direction) {
        if (direction == 'FORWARD')
            return signal == 'GREEN';
        if (direction == 'LEFT')
            return signal == 'LEFT';
        if (direction == 'RIGHT')
            return signal == 'RIGHT';
        return false;
    }

    async run(signal) {
        if (this.checkDirection(signal, 'FORWARD'))
            this.applyDirection('FORWARD');
        if (this.checkDirection(signal, 'LEFT'))
            this.applyDirection('LEFT');
        if (this.checkDirection(signal, 'RIGHT'))
            this.applyDirection('RIGHT');
    }

    constructor(signal, trafficLightController) {
        this.signal = signal;
        this.directions = {
            FORWARD: [],
            LEFT: [],
            RIGHT: [],
        }

        trafficLightController.subscribe((signal) => {
            this.signal = signal;
            this.run(signal);
        })
    }

    async go(direction) {
        return new Promise((resolve, reject) => {
            if (this.checkDirection(this.signal, direction)) {
                return resolve();
            }
            this.directions[direction].push(resolve);
        });
    }
}

exports.Traffic = Traffic;
