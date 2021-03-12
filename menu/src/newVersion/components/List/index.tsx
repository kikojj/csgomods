import React from "react";
import { join } from "../utils";
import { useStyles } from "./styles";

export type ListProps = {
  items?: { content: React.ReactChild; onClick?: () => void; selected: boolean }[];
  marginTop?: number;
};
export const List: React.FC<ListProps> = ({ items = [], marginTop = 20 }) => {
  const classes = useStyles();

  return (
    <div style={{ marginTop }}>
      {items.map((item, key) => (
        <div
          key={key}
          className={join(classes.item, item.selected ? `${classes.item}-selected` : undefined)}
          onClick={item.onClick}
        >
          {item.content}
        </div>
      ))}
    </div>
  );
};
