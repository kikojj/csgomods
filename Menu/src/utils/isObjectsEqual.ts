export function isObjectsEqual<T extends Object, U extends Object>(obj1: T, obj2: U) {
  let isEqual = true;

  Object.keys(obj1).forEach((key) => {
    if (
      !obj1.hasOwnProperty(key) ||
      !obj2.hasOwnProperty(key) ||
      typeof obj1[key as keyof T] !== typeof obj2[key as keyof U] ||
      (obj1[key as keyof T] as any) !== (obj2[key as keyof U] as any)
    ) {
      isEqual = false;
    }
  });

  Object.keys(obj2).forEach((key) => {
    if (
      !obj1.hasOwnProperty(key) ||
      !obj2.hasOwnProperty(key) ||
      typeof obj1[key as keyof T] !== typeof obj2[key as keyof U] ||
      (obj1[key as keyof T] as any) !== (obj2[key as keyof U] as any)
    ) {
      isEqual = false;
    }
  });

  return isEqual;
}
