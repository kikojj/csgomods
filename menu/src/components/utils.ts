export const join = (...classes: (string | undefined | boolean)[]) => {
  let result = "";
  classes.forEach((className, i) => {
    if (className && typeof className === "string") {
      result += `${i === 0 ? "" : " "}${className}`;
    }
  });
  return result;
};
