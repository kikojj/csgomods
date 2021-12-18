import React from "react";
import { join } from "@components/utils";
import { useStyles } from "./styles";

export type ListItemProps = {
  content: React.ReactChild;
  selected?: boolean;
  onClick?: () => void;
};
export const ListItem: React.FC<ListItemProps> = ({
  content,
  selected,
  onClick,
}) => {
  const classes = useStyles();

  return (
    <div
      className={join(
        classes.item,
        onClick ? `${classes.item}-active` : undefined,
        selected ? `${classes.item}-selected` : undefined
      )}
      onClick={onClick}
    >
      {content}
    </div>
  );
};
