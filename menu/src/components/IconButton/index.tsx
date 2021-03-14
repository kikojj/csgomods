import React from "react";

import { join } from "../utils";

import { useStyles } from "./styles";

export type IconButtonProps = {
  className?: string;
  iconUrl: string;
};
export const IconButton: React.FC<IconButtonProps> = ({ className, iconUrl }) => {
  const classes = useStyles();

  return (
    <div className={join(classes.contanier, className)}>
      <img src={iconUrl} />
    </div>
  );
};
