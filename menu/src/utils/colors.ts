export const colors = {
  primary: "#3F51B5",
  green: "#19D220",
  yellow: "#FFBE2F",
  red: "#FF5F58",
  black: "rgba(0,0,0,0.9)",
};

export const colors_ = {
  primary: "#1A73E8",
  secondary: "#16191C",
  teritary: "#1C2430",
  gray: "#4B535C",
  lightGray: "#646465",
  darkBlue: "#161E27",
  blue: "#234062",
  blue2: "#15283E",
};

const percentToHex = (p: number) => {
  const percent = Math.max(0, Math.min(100, p));
  const intValue = Math.round((p / 100) * 255);
  const hexValue = intValue.toString(16);
  return hexValue.padStart(2, "0").toUpperCase();
};

export const hexAlpha = (hex: string, alpha: number) => `${hex}${percentToHex(alpha)}`;

const componentToHex = (c: number) => {
  var hex = c.toString(16);
  return hex.length == 1 ? "0" + hex : hex;
};

export const rgbToHex = (r: number, g: number, b: number) => {
  return "#" + componentToHex(r) + componentToHex(g) + componentToHex(b);
};
