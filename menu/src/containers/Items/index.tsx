import { ItemCard, ItemCardProps } from "@components";
import React from "react";

export type ItemsProps = {
  className?: string;
  data: ItemCardProps[];
};
export const Items: React.FC<ItemsProps> = ({ className, data }) => {
  return (
    <div className={className}>
      {data.map((d, key) => (
        <ItemCard key={key} {...d} />
      ))}
    </div>
  );
};
