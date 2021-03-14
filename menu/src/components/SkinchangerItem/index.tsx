import React from "react";

import { SkinRarity } from "@utils";

import { useStyles } from "./styles";

export type SkinchangerItemProps = {
  image: string;
  alt?: string;
  name: string;
  onClick?: () => void;
  rarity?: SkinRarity;
  active?: boolean;
};
export const SkinchangerItem: React.FC<SkinchangerItemProps> = ({
  image,
  alt,
  name,
  onClick,
  rarity = SkinRarity.RARITY_COMMON,
  active = false,
}) => {
  const classes = useStyles({ rarity, active });

  return (
    <div className={classes.background} onClick={onClick}>
      <div className={classes.content}>
        <img className={classes.image} src={image} alt={alt} />
        <h5 className={classes.name}>{name}</h5>
      </div>
    </div>
  );
};
