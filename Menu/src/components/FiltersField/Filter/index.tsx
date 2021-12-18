import React from "react";
import { join } from "@components/utils";
import { useStyles } from "./styles";

export type FilterProps = {
  filter: string;
  checked: boolean;
  values: string[];
  onChange: (state: string[]) => void;
};
export const Filter: React.FC<FilterProps> = ({
  filter,
  checked,
  values,
  onChange,
}) => {
  const classes = useStyles();

  return (
    <div>
      <div
        className={join(classes.filter, checked && `${classes.filter}-active`)}
        onClick={() =>
          checked
            ? onChange(values.filter((v) => v !== filter))
            : onChange([...values, filter])
        }
      >
        {filter}
      </div>
    </div>
  );
};
