import React from "react";
import { join } from "@components/utils";
import { appName } from "@utils";
import { LogoImage } from "./images";
import { useStyles } from "./styles";

export type LogoProps = {
  className?: string;
  useText?: boolean;
  size?: "small" | "large";
};
export const Logo: React.FC<LogoProps> = ({ className, useText = true, size = "small" }) => {
  const classes = useStyles({ size });

  if (!useText) {
    return <img className={join(classes.image, className)} src={LogoImage} alt="logo" />;
  }
  
  return (
    <div className={join(classes.container, className)}>
      <img className={classes.image} src={LogoImage} alt="logo" />
      <h2 className={classes.text}>{appName}</h2>
    </div>
  );
};
