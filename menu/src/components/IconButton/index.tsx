import React from "react";
import { join } from "@components/utils";
import { useStyles } from "./styles";

export type IconButtonProps = {
  iconUrl: string;
  className?: string;
};
export const IconButton: React.FC<IconButtonProps> = ({ className, iconUrl }) => {
  const classes = useStyles();

  return (
    <div className={join(classes.container, className)}>
      <img src={iconUrl} />
    </div>
  );
};
