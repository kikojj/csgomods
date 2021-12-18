import React from "react";
import { SkinRarity } from "@utils";
import { useStyles } from "./styles";

export type SkinchangerItemProps = {
  name: string;
  active?: boolean;
  image: string;
  rarity?: SkinRarity;
  onClick?: () => void;
};
export const SkinchangerItem: React.FC<SkinchangerItemProps> = ({
  name,
  active = false,
  image,
  rarity = SkinRarity.RARITY_COMMON,
  onClick,
}) => {
  const classes = useStyles({ rarity, active, url: image });

  return (
    <div className={classes.background} onClick={onClick}>
      <div className={classes.content}>
        <div className={classes.image} />
        <h5 className={classes.name}>{name}</h5>
      </div>
    </div>
  );
};
