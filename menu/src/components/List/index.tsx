import React from "react";
import { ListItem, ListItemProps } from "./ListItem";
import { useStyles } from "./styles";

export type ListProps = {
  items?: ListItemProps[];
  marginTop?: number;
};
export const List: React.FC<ListProps> = ({ items = [], marginTop = 20 }) => {
  const classes = useStyles({marginTop});

  const listItems = React.useMemo(
    () => items.map((item, key) => <ListItem key={key} {...item} />),
    [items]
  );

  return <div className={classes.container}>{listItems}</div>;
};
