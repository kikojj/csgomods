export const join = (...classes: (string | undefined)[]) => {
  let result = "";
  classes.forEach((className, i) => {
    if (className) {
      result += `${i === 0 ? "" : " "}${className}`;
    }
  });
  return result;
};
