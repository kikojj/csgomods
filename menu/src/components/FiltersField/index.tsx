import React from "react";

import { join } from "../utils";

import { useStyles } from "./styles";

export type FiltersFieldProps = {
  label?: string;
  helperText?: string;
  filters?: string[];
  values?: string[];
  onChange?: (v: string[]) => void;
  marginTop?: number;
};
export const FiltersField: React.FC<FiltersFieldProps> = ({
  label = "Filters:",
  helperText,
  filters = ["Value 1", "Value2", "Value3"],
  values: _values,
  onChange: _onChange,
  marginTop = 20,
}) => {
  const classes = useStyles();

  const [__values, __onChange] = React.useState<string[]>([]);

  const values = _values !== undefined && _onChange !== undefined ? _values : __values;
  const onChange = _values !== undefined && _onChange !== undefined ? _onChange : __onChange;

  return (
    <div className={classes.container} style={{ marginTop }}>
      <h5 className={classes.label}>{label}</h5>
      {helperText ? <p className={classes.helperText}>{helperText}</p> : ""}
      <div className={classes.filters}>
        {filters.map((filter, key) => {
          const checked = values.includes(filter);
          return (
            <div key={key}>
              <div
                className={join(classes.filter, checked ? `${classes.filter}-active` : undefined)}
                onClick={() => (checked ? onChange(values.filter((v) => v !== filter)) : onChange([...values, filter]))}
              >
                {filter}
              </div>
            </div>
          );
        })}
      </div>
    </div>
  );
};
