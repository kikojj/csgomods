function isNumber(s: string) {
  return s >= "0" && s <= "9";
}

export function usePhoneHandler(e: React.ChangeEvent<HTMLInputElement>) {
  const value = e.target.value;

  if (isNumber(value[value.length - 1]) && value.length <= 12) {
    if (value[0] !== "+") {
      e.target.value = "+" + e.target.value;
    }
  } else {
    e.target.value = e.target.value.slice(0, e.target.value.length - 1);
  }

  return e;
}

export function useNumberHandler(
  e: React.ChangeEvent<HTMLInputElement>,
  maxLength?: number
) {
  const value = e.target.value;

  if (
    !isNumber(value[value.length - 1]) ||
    (maxLength && value.length > maxLength)
  ) {
    e.target.value = e.target.value.slice(0, e.target.value.length - 1);
  }

  return e;
}
