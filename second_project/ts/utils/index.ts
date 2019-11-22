export const shuffle = (array) => array.sort(() => Math.random() - 0.5);

export const randomInt = (min, max) => {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min;
};


export const randomIntInc = (min, max) => {
  return Math.floor(Math.random() * (max - min + 1) + min);
};

export const count = (array) => array.reduce((counter, item) => {
  counter[item.strategy] = counter.hasOwnProperty(item.strategy) ? counter[item.strategy] + 1 : 1;
  return counter;
}, {});
