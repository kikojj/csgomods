import React from "react";
import { useStyles } from "./styles";

export type SelectItemProps = {
  value: string;
  children: React.ReactNode;
};
export function SelectItem({ value, children }: SelectItemProps) {
  const classes = useStyles();
  return (
    <button className={classes.selectItem} data-value={value}>
      {children}
    </button>
  );
}
