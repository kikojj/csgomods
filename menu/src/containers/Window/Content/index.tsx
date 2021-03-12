import React from "react";
import { useStyles } from "./styles";

export type WindowContentProps = {
  className?: string;
  children?: React.ReactNode;
};
export const WindowContent: React.FC<WindowContentProps> = ({ className, children }) => {
  const classes = useStyles();
  return <div className={classes.bg + (className ? ` ${className}` : "")}>{children}</div>;
};
