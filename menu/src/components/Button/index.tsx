import React from "react";
import { colors } from "@utils";
import { join } from "../utils";
import { useStyles } from "./styles";

export type ButtonProps = {
  children?: React.ReactNode;
  color?: string;
  marginTop?: number;
  marginRight?: number;
  className?: string;
  onClick?: () => void;
};
export const Button: React.FC<ButtonProps> = ({
  children,
  color = colors.primary,
  marginTop = 20,
  marginRight,
  className,
  onClick,
}) => {
  const classes = useStyles({ color, marginRight, marginTop });

  return (
    <div className={join(classes.container, className)} onClick={onClick}>
      {children}
    </div>
  );
};
