import React from "react";

import { colors } from "@utils";
import { join } from "../utils";

import { useStyles } from "./styles";

export type ButtonProps = {
  className?: string;
  onClick?: () => void;
  children?: React.ReactChild;
  marginTop?: number;
  marginRight?: number;
  color?: string;
};
export const Button: React.FC<ButtonProps> = ({
  className,
  children,
  onClick,
  marginTop = 20,
  marginRight,
  color = colors.primary,
}) => {
  const classes = useStyles({ color });
  return (
    <div className={join(classes.container, className)} onClick={onClick} style={{ marginTop, marginRight }}>
      {children}
    </div>
  );
};
