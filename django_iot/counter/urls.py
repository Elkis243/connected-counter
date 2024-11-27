from django.urls import path
from .views import *

urlpatterns = [
    path("", metrics, name="metrics"),
    path('get_metric/', htmx_metrics, name='get_metric'),
    path("<str:name>/", Metric_counter.as_view(), name="data"),
]