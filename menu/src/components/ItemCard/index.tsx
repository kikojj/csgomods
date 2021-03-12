import React from "react";
import { Card, CardActionArea, CardMedia, CardContent, Typography } from "@material-ui/core";
import { useStyles } from "./styles";

export type ItemCardProps = {
  className?: string;
  image: string;
  title: string;
  onClick?: () => void;
};
export const ItemCard: React.FC<ItemCardProps> = ({ className, image, title, onClick }) => {
  const classes = useStyles();
  return (
    <Card className={classes.card + (className ? " " + className : "")} onClick={onClick}>
      <CardActionArea className={classes.card_action}>
        <CardMedia className={classes.card_media} image={image} />
        <CardContent>
          <Typography gutterBottom variant="body1" align="center">
            {title}
          </Typography>
        </CardContent>
      </CardActionArea>
    </Card>
  );
};
