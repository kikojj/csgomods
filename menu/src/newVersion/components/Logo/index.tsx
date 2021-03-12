import React from "react";
import { useStyles } from "./styles";
import LogoPng from "./images/logo.png";
import { join } from "../utils";

export type LogoProps = {
  className?: string;
  useText?: boolean;
  size?: "small" | "large";
};
export const Logo: React.FC<LogoProps> = ({ className, useText = true, size = "small" }) => {
  const classes = useStyles({ size });

  if (!useText) {
    return <img className={join(classes.image, className)} src={LogoPng} alt="logo" />;
  }
  return (
    <div className={join(classes.container, className)}>
      <img className={classes.image} src={LogoPng} alt="logo" />
      <h2 className={classes.text}>csgomods</h2>
    </div>
  );
};
